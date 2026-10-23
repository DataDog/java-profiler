---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-23 16:04:35 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 13 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 52-54 cores)</summary>

```
1792785547 52
1792785552 52
1792785557 52
1792785562 52
1792785567 52
1792785572 54
1792785577 54
1792785582 54
1792785587 54
1792785592 54
1792785597 54
1792785602 54
1792785607 54
1792785612 54
1792785617 54
1792785622 54
1792785627 54
1792785632 54
1792785637 54
1792785642 54
```
</details>

---

