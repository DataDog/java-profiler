---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-24 15:44:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 218 |
| Sample Rate | 3.63/sec |
| Health Score | 227% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 235 |
| Sample Rate | 3.92/sec |
| Health Score | 245% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 69-79 cores)</summary>

```
1787600204 71
1787600209 71
1787600214 71
1787600219 71
1787600224 71
1787600229 69
1787600234 69
1787600239 73
1787600244 73
1787600249 73
1787600254 73
1787600259 73
1787600264 77
1787600269 77
1787600274 79
1787600279 79
1787600284 79
1787600289 79
1787600294 79
1787600299 79
```
</details>

---

