---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-24 07:06:37 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 281 |
| Sample Rate | 4.68/sec |
| Health Score | 292% |
| Threads | 12 |
| Allocations | 144 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795521778 64
1795521783 64
1795521788 64
1795521793 64
1795521798 64
1795521803 64
1795521808 64
1795521813 64
1795521818 64
1795521823 64
1795521829 64
1795521834 64
1795521839 33
1795521844 33
1795521849 33
1795521854 33
1795521859 33
1795521864 33
1795521869 33
1795521874 33
```
</details>

---

