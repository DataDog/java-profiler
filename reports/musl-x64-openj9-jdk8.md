---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-23 05:22:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 176 |
| Sample Rate | 2.93/sec |
| Health Score | 183% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 173 |
| Sample Rate | 2.88/sec |
| Health Score | 180% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 47-84 cores)</summary>

```
1795429063 84
1795429068 84
1795429073 82
1795429078 82
1795429083 82
1795429088 82
1795429093 82
1795429098 49
1795429103 49
1795429108 49
1795429113 49
1795429118 49
1795429123 49
1795429128 47
1795429133 47
1795429138 47
1795429143 47
1795429148 47
1795429153 47
1795429158 47
```
</details>

---

