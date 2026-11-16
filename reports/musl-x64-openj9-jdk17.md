---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 11:44:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 789 |
| Sample Rate | 13.15/sec |
| Health Score | 822% |
| Threads | 12 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (4 unique values: 65-72 cores)</summary>

```
1794847082 65
1794847087 65
1794847092 65
1794847097 67
1794847102 67
1794847107 67
1794847112 67
1794847117 67
1794847122 69
1794847127 69
1794847132 69
1794847137 69
1794847142 69
1794847147 69
1794847152 69
1794847157 69
1794847162 69
1794847167 69
1794847172 69
1794847177 69
```
</details>

---

