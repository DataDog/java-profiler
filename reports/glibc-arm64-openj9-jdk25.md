---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-22 00:01:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 12 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 13 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (2 unique values: 25-26 cores)</summary>

```
1795323506 26
1795323511 26
1795323516 26
1795323521 26
1795323526 26
1795323531 26
1795323536 26
1795323541 26
1795323546 25
1795323551 25
1795323556 25
1795323561 25
1795323566 25
1795323571 25
1795323576 25
1795323581 25
1795323586 25
1795323591 25
1795323596 26
1795323601 26
```
</details>

---

