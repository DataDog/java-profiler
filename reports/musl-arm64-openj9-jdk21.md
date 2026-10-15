---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-15 12:04:41 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 7 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1792079963 40
1792079968 40
1792079973 40
1792079978 40
1792079983 38
1792079988 38
1792079993 38
1792079998 38
1792080003 38
1792080008 38
1792080013 38
1792080018 38
1792080023 40
1792080028 40
1792080033 40
1792080038 40
1792080043 40
1792080048 40
1792080053 40
1792080058 40
```
</details>

---

