---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 07:31:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 320 |
| Sample Rate | 5.33/sec |
| Health Score | 333% |
| Threads | 12 |
| Allocations | 165 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1794572803 31
1794572808 31
1794572813 31
1794572818 31
1794572823 31
1794572828 36
1794572833 36
1794572838 36
1794572843 36
1794572848 36
1794572853 36
1794572858 36
1794572863 36
1794572868 36
1794572873 36
1794572878 36
1794572883 36
1794572888 36
1794572893 36
1794572898 36
```
</details>

---

