---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 09:18:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794492762 46
1794492767 46
1794492772 46
1794492777 46
1794492782 46
1794492787 46
1794492792 46
1794492797 46
1794492802 46
1794492807 46
1794492812 51
1794492817 51
1794492822 51
1794492827 51
1794492832 51
1794492837 51
1794492842 51
1794492847 51
1794492852 51
1794492857 51
```
</details>

---

