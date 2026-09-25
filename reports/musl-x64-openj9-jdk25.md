---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-25 14:37:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 10 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (2 unique values: 62-63 cores)</summary>

```
1790361180 63
1790361185 63
1790361190 63
1790361195 63
1790361200 63
1790361205 63
1790361210 63
1790361215 63
1790361220 63
1790361225 63
1790361230 63
1790361235 63
1790361240 62
1790361245 62
1790361250 62
1790361255 62
1790361260 62
1790361265 62
1790361270 62
1790361275 62
```
</details>

---

