---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-24 05:55:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 8 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 208 |
| Sample Rate | 3.47/sec |
| Health Score | 217% |
| Threads | 10 |
| Allocations | 126 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1792835470 43
1792835475 43
1792835480 43
1792835485 43
1792835490 43
1792835495 43
1792835500 43
1792835505 43
1792835510 43
1792835515 43
1792835520 48
1792835525 48
1792835530 48
1792835535 48
1792835540 48
1792835545 48
1792835550 47
1792835555 47
1792835560 47
1792835565 47
```
</details>

---

