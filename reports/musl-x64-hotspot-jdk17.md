---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-04 12:28:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 686 |
| Sample Rate | 11.43/sec |
| Health Score | 714% |
| Threads | 10 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (3 unique values: 59-68 cores)</summary>

```
1793812787 62
1793812792 62
1793812797 62
1793812802 68
1793812807 68
1793812812 68
1793812817 68
1793812822 68
1793812827 68
1793812832 68
1793812837 68
1793812842 68
1793812847 59
1793812852 59
1793812857 59
1793812862 59
1793812867 59
1793812873 59
1793812878 59
1793812883 59
```
</details>

---

