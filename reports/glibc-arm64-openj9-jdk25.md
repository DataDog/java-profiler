---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-12 14:04:30 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 11 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1786557626 48
1786557631 48
1786557636 48
1786557641 48
1786557646 48
1786557651 48
1786557656 43
1786557661 43
1786557666 43
1786557671 43
1786557676 43
1786557681 43
1786557686 43
1786557691 43
1786557696 43
1786557701 43
1786557706 43
1786557711 48
1786557716 48
1786557721 48
```
</details>

---

