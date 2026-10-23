---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-23 16:04:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 390 |
| Sample Rate | 6.50/sec |
| Health Score | 406% |
| Threads | 12 |
| Allocations | 143 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 16 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 49-54 cores)</summary>

```
1792785537 54
1792785542 54
1792785547 54
1792785552 54
1792785557 54
1792785562 54
1792785567 54
1792785572 54
1792785577 49
1792785582 49
1792785587 49
1792785592 49
1792785597 49
1792785602 49
1792785607 49
1792785612 49
1792785617 49
1792785622 49
1792785627 49
1792785632 49
```
</details>

---

