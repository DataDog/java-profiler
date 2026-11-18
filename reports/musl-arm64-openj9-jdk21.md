---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 09:30:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 295 |
| Sample Rate | 4.92/sec |
| Health Score | 308% |
| Threads | 10 |
| Allocations | 152 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (4 unique values: 32-64 cores)</summary>

```
1795011903 32
1795011908 45
1795011913 45
1795011918 45
1795011923 45
1795011928 45
1795011933 45
1795011938 45
1795011943 58
1795011948 58
1795011953 58
1795011958 58
1795011963 58
1795011968 58
1795011973 58
1795011978 58
1795011983 58
1795011988 58
1795011993 58
1795011998 58
```
</details>

---

