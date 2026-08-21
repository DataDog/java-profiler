---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-21 07:48:14 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 958 |
| Sample Rate | 15.97/sec |
| Health Score | 998% |
| Threads | 9 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1787312627 43
1787312632 43
1787312637 43
1787312642 43
1787312647 43
1787312652 43
1787312657 43
1787312662 43
1787312667 43
1787312672 43
1787312677 43
1787312682 43
1787312687 43
1787312692 38
1787312697 38
1787312702 38
1787312708 38
1787312713 38
1787312718 38
1787312723 38
```
</details>

---

