---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-20 10:11:01 EDT

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 641 |
| Sample Rate | 10.68/sec |
| Health Score | 668% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 876 |
| Sample Rate | 14.60/sec |
| Health Score | 912% |
| Threads | 9 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (5 unique values: 78-85 cores)</summary>

```
1792505002 83
1792505007 85
1792505012 85
1792505017 85
1792505022 85
1792505027 85
1792505032 85
1792505037 85
1792505042 85
1792505047 82
1792505052 82
1792505057 82
1792505062 82
1792505067 78
1792505072 78
1792505077 78
1792505082 78
1792505087 82
1792505092 82
1792505097 82
```
</details>

---

