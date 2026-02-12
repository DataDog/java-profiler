---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-12 08:15:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 903 |
| Sample Rate | 15.05/sec |
| Health Score | 941% |
| Threads | 12 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1770901631 32
1770901636 32
1770901641 32
1770901646 32
1770901651 32
1770901656 32
1770901661 32
1770901666 32
1770901671 32
1770901676 32
1770901681 32
1770901686 32
1770901691 32
1770901696 32
1770901701 32
1770901706 32
1770901711 32
1770901716 32
1770901721 32
1770901726 32
```
</details>

---

