---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-25 07:51:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 33-33 cores)</summary>

```
1795610788 33
1795610793 33
1795610798 33
1795610803 33
1795610808 33
1795610813 33
1795610818 33
1795610823 33
1795610828 33
1795610833 33
1795610838 33
1795610843 33
1795610848 33
1795610853 33
1795610858 33
1795610863 33
1795610868 33
1795610873 33
1795610878 33
1795610883 33
```
</details>

---

