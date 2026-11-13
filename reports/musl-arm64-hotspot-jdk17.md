---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 07:31:29 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 803 |
| Sample Rate | 13.38/sec |
| Health Score | 836% |
| Threads | 12 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794572803 43
1794572808 43
1794572813 43
1794572818 43
1794572823 43
1794572828 48
1794572833 48
1794572838 48
1794572843 48
1794572848 43
1794572853 43
1794572858 43
1794572863 43
1794572868 43
1794572873 43
1794572878 43
1794572883 43
1794572888 43
1794572893 43
1794572898 43
```
</details>

---

