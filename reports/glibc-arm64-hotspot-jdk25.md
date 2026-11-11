---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 20:36:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 222 |
| Sample Rate | 3.70/sec |
| Health Score | 231% |
| Threads | 11 |
| Allocations | 150 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 195 |
| Sample Rate | 3.25/sec |
| Health Score | 203% |
| Threads | 14 |
| Allocations | 120 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1794360789 48
1794360794 48
1794360799 48
1794360804 48
1794360809 48
1794360814 48
1794360819 48
1794360824 48
1794360829 48
1794360834 48
1794360839 48
1794360844 48
1794360849 48
1794360854 48
1794360859 48
1794360864 40
1794360869 40
1794360874 40
1794360879 40
1794360884 40
```
</details>

---

