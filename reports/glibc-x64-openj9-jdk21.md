---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-13 10:31:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 460 |
| Sample Rate | 7.67/sec |
| Health Score | 479% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 723 |
| Sample Rate | 12.05/sec |
| Health Score | 753% |
| Threads | 11 |
| Allocations | 427 |

<details>
<summary>CPU Timeline (5 unique values: 24-58 cores)</summary>

```
1791901641 24
1791901646 24
1791901651 24
1791901656 24
1791901661 24
1791901666 41
1791901671 41
1791901676 58
1791901681 58
1791901686 58
1791901691 58
1791901696 58
1791901701 58
1791901706 58
1791901711 58
1791901716 58
1791901721 58
1791901726 58
1791901731 58
1791901736 52
```
</details>

---

