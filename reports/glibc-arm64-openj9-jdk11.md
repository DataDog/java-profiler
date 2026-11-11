---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 12:34:02 EST

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
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 946 |
| Sample Rate | 15.77/sec |
| Health Score | 986% |
| Threads | 9 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (4 unique values: 33-48 cores)</summary>

```
1794418100 48
1794418105 48
1794418110 48
1794418115 48
1794418120 48
1794418125 48
1794418130 43
1794418135 43
1794418140 38
1794418145 38
1794418150 38
1794418155 38
1794418160 38
1794418165 38
1794418170 38
1794418175 38
1794418180 33
1794418185 33
1794418190 33
1794418195 33
```
</details>

---

