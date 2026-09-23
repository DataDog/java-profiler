---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-23 10:08:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 886 |
| Sample Rate | 14.77/sec |
| Health Score | 923% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (3 unique values: 46-49 cores)</summary>

```
1790172198 49
1790172203 49
1790172208 47
1790172213 47
1790172218 49
1790172223 49
1790172228 49
1790172233 49
1790172238 49
1790172243 47
1790172248 47
1790172253 47
1790172258 47
1790172263 47
1790172269 47
1790172274 47
1790172279 47
1790172284 47
1790172289 47
1790172294 47
```
</details>

---

