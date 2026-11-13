---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 00:07:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 279 |
| Sample Rate | 4.65/sec |
| Health Score | 291% |
| Threads | 12 |
| Allocations | 149 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1794546224 38
1794546229 38
1794546234 38
1794546239 38
1794546244 38
1794546249 43
1794546254 43
1794546259 43
1794546264 43
1794546269 43
1794546274 43
1794546279 43
1794546284 43
1794546289 43
1794546294 43
1794546299 43
1794546304 43
1794546309 43
1794546314 43
1794546319 43
```
</details>

---

