---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-11 01:02:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 327 |
| Sample Rate | 5.45/sec |
| Health Score | 341% |
| Threads | 13 |
| Allocations | 96 |

<details>
<summary>CPU Timeline (2 unique values: 16-18 cores)</summary>

```
1791694723 16
1791694728 16
1791694733 16
1791694738 16
1791694743 16
1791694748 16
1791694753 16
1791694758 16
1791694763 16
1791694768 16
1791694773 18
1791694778 18
1791694783 18
1791694788 18
1791694794 18
1791694799 18
1791694804 18
1791694809 18
1791694814 18
1791694819 18
```
</details>

---

