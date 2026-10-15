---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-15 12:04:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 9 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 15 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1792080002 51
1792080007 51
1792080012 51
1792080017 51
1792080022 51
1792080027 51
1792080032 51
1792080037 51
1792080042 51
1792080047 51
1792080052 51
1792080057 51
1792080062 51
1792080067 51
1792080072 51
1792080077 51
1792080082 46
1792080087 46
1792080092 46
1792080097 46
```
</details>

---

