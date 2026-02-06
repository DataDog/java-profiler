---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-06 10:50:46 EST

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 10 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 13 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (3 unique values: 86-96 cores)</summary>

```
1770392737 96
1770392742 96
1770392747 96
1770392752 96
1770392757 96
1770392762 96
1770392767 96
1770392772 96
1770392777 96
1770392782 96
1770392787 96
1770392792 96
1770392797 96
1770392802 96
1770392807 91
1770392812 91
1770392817 86
1770392822 86
1770392827 86
1770392832 86
```
</details>

---

