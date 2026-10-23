---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-23 16:04:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 10 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1792785532 34
1792785537 34
1792785542 34
1792785547 34
1792785552 34
1792785557 34
1792785562 34
1792785567 34
1792785572 34
1792785577 34
1792785582 34
1792785587 34
1792785592 29
1792785597 29
1792785602 29
1792785607 29
1792785612 29
1792785617 29
1792785622 29
1792785627 29
```
</details>

---

