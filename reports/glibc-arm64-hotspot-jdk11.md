---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 05:16:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 9 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (3 unique values: 43-47 cores)</summary>

```
1794823696 47
1794823701 47
1794823706 46
1794823711 46
1794823716 46
1794823721 46
1794823726 47
1794823731 47
1794823736 46
1794823741 46
1794823746 43
1794823751 43
1794823756 43
1794823761 43
1794823766 43
1794823771 43
1794823776 43
1794823781 43
1794823786 43
1794823791 43
```
</details>

---

