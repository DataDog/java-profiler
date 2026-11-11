---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 09:46:15 EST

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
| CPU Cores (start) | 93 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 718 |
| Sample Rate | 11.97/sec |
| Health Score | 748% |
| Threads | 9 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (4 unique values: 91-96 cores)</summary>

```
1794408067 93
1794408072 93
1794408077 93
1794408082 93
1794408087 93
1794408092 93
1794408097 93
1794408102 93
1794408107 93
1794408112 91
1794408117 91
1794408122 91
1794408127 91
1794408132 94
1794408137 94
1794408142 94
1794408147 96
1794408152 96
1794408157 96
1794408162 96
```
</details>

---

