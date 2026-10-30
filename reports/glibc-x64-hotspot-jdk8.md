---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-30 09:38:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 11 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 173 |
| Sample Rate | 2.88/sec |
| Health Score | 180% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 274 |
| Sample Rate | 4.57/sec |
| Health Score | 286% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 9-11 cores)</summary>

```
1793367169 11
1793367174 11
1793367179 11
1793367184 11
1793367189 11
1793367194 11
1793367199 11
1793367204 11
1793367209 11
1793367214 11
1793367219 11
1793367224 11
1793367229 11
1793367234 11
1793367239 9
1793367244 9
1793367249 9
1793367254 9
1793367259 9
1793367264 9
```
</details>

---

