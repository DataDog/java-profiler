---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-19 05:04:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 10 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 342 |
| Sample Rate | 5.70/sec |
| Health Score | 356% |
| Threads | 13 |
| Allocations | 138 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792400072 48
1792400077 48
1792400082 48
1792400087 48
1792400092 48
1792400097 48
1792400102 48
1792400107 48
1792400112 48
1792400117 48
1792400122 48
1792400127 48
1792400132 48
1792400137 48
1792400142 48
1792400147 43
1792400152 43
1792400157 43
1792400162 43
1792400167 43
```
</details>

---

