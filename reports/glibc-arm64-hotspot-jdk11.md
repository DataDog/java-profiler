---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-11 01:02:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 11 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 9 |
| Allocations | 40 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 11 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 11-16 cores)</summary>

```
1791694693 11
1791694698 11
1791694703 11
1791694708 11
1791694713 11
1791694718 11
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
1791694773 16
1791694778 16
1791694783 16
1791694788 16
```
</details>

---

