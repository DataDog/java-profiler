---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-08 10:10:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 203 |
| Sample Rate | 3.38/sec |
| Health Score | 211% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 245 |
| Sample Rate | 4.08/sec |
| Health Score | 255% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 58-69 cores)</summary>

```
1791468230 63
1791468235 63
1791468240 63
1791468245 63
1791468250 63
1791468255 63
1791468260 63
1791468265 58
1791468270 58
1791468275 58
1791468280 58
1791468285 58
1791468290 58
1791468295 58
1791468300 69
1791468305 69
1791468310 69
1791468315 69
1791468320 69
1791468325 69
```
</details>

---

