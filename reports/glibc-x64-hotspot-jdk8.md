---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-13 00:07:34 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 320 |
| Sample Rate | 5.33/sec |
| Health Score | 333% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 406 |
| Sample Rate | 6.77/sec |
| Health Score | 423% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 46-79 cores)</summary>

```
1794546179 51
1794546184 51
1794546189 51
1794546194 51
1794546199 51
1794546204 51
1794546209 51
1794546214 51
1794546219 51
1794546224 51
1794546229 51
1794546234 51
1794546239 51
1794546244 51
1794546249 51
1794546254 51
1794546259 51
1794546264 79
1794546269 79
1794546274 46
```
</details>

---

