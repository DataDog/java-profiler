---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 13:36:50 EST

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 826 |
| Sample Rate | 13.77/sec |
| Health Score | 861% |
| Threads | 11 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (5 unique values: 59-65 cores)</summary>

```
1795113133 61
1795113138 61
1795113143 61
1795113148 61
1795113153 61
1795113158 61
1795113163 61
1795113168 61
1795113173 61
1795113178 59
1795113183 59
1795113188 59
1795113193 59
1795113198 62
1795113203 62
1795113208 62
1795113213 62
1795113218 62
1795113223 62
1795113228 62
```
</details>

---

