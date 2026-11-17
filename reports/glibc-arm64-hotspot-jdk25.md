---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-17 14:55:31 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 12 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 14 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794945059 51
1794945064 51
1794945069 51
1794945074 51
1794945079 51
1794945084 51
1794945089 51
1794945094 51
1794945099 51
1794945104 51
1794945109 51
1794945114 51
1794945119 51
1794945124 51
1794945129 51
1794945134 51
1794945139 51
1794945144 51
1794945149 51
1794945154 51
```
</details>

---

