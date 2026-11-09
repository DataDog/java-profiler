---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-09 11:10:57 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 8 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 755 |
| Sample Rate | 12.58/sec |
| Health Score | 786% |
| Threads | 10 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (4 unique values: 63-69 cores)</summary>

```
1794240163 63
1794240168 65
1794240173 65
1794240178 65
1794240183 65
1794240188 65
1794240193 65
1794240198 65
1794240203 65
1794240208 67
1794240213 67
1794240218 67
1794240223 67
1794240228 67
1794240233 67
1794240238 67
1794240243 69
1794240248 69
1794240253 69
1794240258 69
```
</details>

---

