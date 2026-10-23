---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-23 16:04:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 766 |
| Sample Rate | 12.77/sec |
| Health Score | 798% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 6 |
| Allocations | 24 |

<details>
<summary>CPU Timeline (2 unique values: 36-41 cores)</summary>

```
1792785562 41
1792785567 41
1792785572 41
1792785577 41
1792785582 41
1792785587 41
1792785592 41
1792785597 41
1792785602 41
1792785607 41
1792785612 41
1792785617 41
1792785622 41
1792785627 41
1792785632 41
1792785637 41
1792785642 41
1792785647 41
1792785652 41
1792785657 41
```
</details>

---

