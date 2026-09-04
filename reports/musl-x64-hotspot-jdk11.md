---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-04 05:50:52 EDT

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 8 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 946 |
| Sample Rate | 15.77/sec |
| Health Score | 986% |
| Threads | 10 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (3 unique values: 90-96 cores)</summary>

```
1788515189 90
1788515194 90
1788515199 90
1788515204 90
1788515209 90
1788515214 90
1788515219 90
1788515224 90
1788515229 90
1788515234 92
1788515239 92
1788515244 92
1788515249 92
1788515254 92
1788515259 96
1788515264 96
1788515269 96
1788515274 96
1788515279 96
1788515284 96
```
</details>

---

