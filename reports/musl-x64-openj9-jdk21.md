---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-13 12:15:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 735 |
| Sample Rate | 12.25/sec |
| Health Score | 766% |
| Threads | 11 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 879 |
| Sample Rate | 14.65/sec |
| Health Score | 916% |
| Threads | 13 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (2 unique values: 70-74 cores)</summary>

```
1773418140 74
1773418145 74
1773418150 74
1773418155 74
1773418160 74
1773418165 74
1773418170 74
1773418175 70
1773418180 70
1773418185 70
1773418190 70
1773418195 70
1773418200 70
1773418205 70
1773418210 70
1773418215 70
1773418220 70
1773418225 70
1773418230 70
1773418235 70
```
</details>

---

