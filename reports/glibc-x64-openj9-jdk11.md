---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-19 05:04:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 8 |
| Allocations | 319 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 756 |
| Sample Rate | 12.60/sec |
| Health Score | 787% |
| Threads | 9 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (4 unique values: 87-94 cores)</summary>

```
1792400072 94
1792400077 89
1792400082 89
1792400087 87
1792400092 87
1792400097 89
1792400102 89
1792400107 89
1792400112 89
1792400117 89
1792400122 89
1792400127 91
1792400132 91
1792400137 91
1792400142 91
1792400147 91
1792400152 91
1792400157 91
1792400162 91
1792400167 91
```
</details>

---

