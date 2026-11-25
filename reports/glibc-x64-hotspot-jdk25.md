---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 13:30:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 10 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (4 unique values: 75-83 cores)</summary>

```
1795631113 83
1795631118 83
1795631123 83
1795631128 83
1795631133 81
1795631138 81
1795631143 81
1795631148 81
1795631153 81
1795631158 81
1795631163 77
1795631168 77
1795631173 77
1795631178 77
1795631183 77
1795631188 77
1795631193 75
1795631198 75
1795631203 75
1795631208 75
```
</details>

---

