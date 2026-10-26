---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-26 09:38:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 15 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1793021586 48
1793021591 48
1793021596 48
1793021601 48
1793021606 48
1793021611 48
1793021616 48
1793021621 48
1793021626 48
1793021631 48
1793021636 48
1793021641 48
1793021646 48
1793021651 48
1793021656 48
1793021661 48
1793021666 48
1793021671 43
1793021676 43
1793021681 38
```
</details>

---

