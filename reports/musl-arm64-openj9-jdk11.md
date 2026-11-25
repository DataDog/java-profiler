---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 05:36:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 10 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (2 unique values: 21-33 cores)</summary>

```
1795602630 33
1795602635 21
1795602640 21
1795602645 21
1795602650 21
1795602655 21
1795602661 21
1795602666 21
1795602671 21
1795602676 21
1795602681 21
1795602686 21
1795602691 21
1795602696 21
1795602701 21
1795602706 21
1795602711 21
1795602716 21
1795602721 21
1795602726 21
```
</details>

---

