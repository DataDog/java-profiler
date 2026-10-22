---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 06:47:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 8 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (5 unique values: 78-83 cores)</summary>

```
1792665761 83
1792665766 83
1792665771 83
1792665776 83
1792665781 83
1792665786 83
1792665791 83
1792665796 79
1792665801 79
1792665806 79
1792665811 79
1792665816 82
1792665821 82
1792665826 80
1792665831 80
1792665836 80
1792665841 80
1792665846 80
1792665851 78
1792665856 78
```
</details>

---

