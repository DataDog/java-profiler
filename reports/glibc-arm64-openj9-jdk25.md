---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-14 08:32:11 EDT

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 6 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 12 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (2 unique values: 6-18 cores)</summary>

```
1791980608 18
1791980613 18
1791980618 18
1791980623 18
1791980628 6
1791980633 6
1791980638 6
1791980643 6
1791980648 6
1791980653 6
1791980658 6
1791980663 6
1791980668 6
1791980673 6
1791980678 6
1791980683 6
1791980688 6
1791980693 6
1791980698 6
1791980703 6
```
</details>

---

