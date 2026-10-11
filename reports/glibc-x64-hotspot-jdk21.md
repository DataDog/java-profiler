---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-11 01:02:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 9 |
| Allocations | 311 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 11 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (3 unique values: 39-61 cores)</summary>

```
1791694712 41
1791694717 41
1791694722 41
1791694727 41
1791694732 41
1791694737 41
1791694742 41
1791694747 41
1791694752 41
1791694757 41
1791694762 41
1791694767 41
1791694772 41
1791694777 39
1791694782 39
1791694787 39
1791694792 39
1791694797 39
1791694802 39
1791694807 39
```
</details>

---

