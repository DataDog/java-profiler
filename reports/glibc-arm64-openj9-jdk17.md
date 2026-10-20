---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-20 10:11:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 8 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 14 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (2 unique values: 9-29 cores)</summary>

```
1792505022 9
1792505027 9
1792505032 9
1792505037 9
1792505042 9
1792505047 9
1792505052 9
1792505057 9
1792505062 9
1792505067 29
1792505072 29
1792505077 29
1792505082 29
1792505087 29
1792505092 29
1792505097 29
1792505102 29
1792505107 29
1792505112 29
1792505117 29
```
</details>

---

