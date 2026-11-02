---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 06:22:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 454 |
| Sample Rate | 7.57/sec |
| Health Score | 473% |
| Threads | 8 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 9 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (3 unique values: 59-63 cores)</summary>

```
1793618310 60
1793618315 60
1793618320 63
1793618325 63
1793618330 63
1793618335 63
1793618340 63
1793618345 63
1793618350 63
1793618355 63
1793618360 63
1793618365 63
1793618370 63
1793618375 63
1793618380 63
1793618385 63
1793618390 63
1793618395 63
1793618400 63
1793618405 63
```
</details>

---

