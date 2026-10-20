---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-20 10:08:02 EDT

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
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 11 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (2 unique values: 38-48 cores)</summary>

```
1792505042 48
1792505047 48
1792505052 38
1792505057 38
1792505062 38
1792505067 38
1792505072 38
1792505077 38
1792505082 38
1792505087 38
1792505092 38
1792505097 38
1792505102 38
1792505107 38
1792505112 38
1792505117 38
1792505122 38
1792505127 38
1792505132 38
1792505137 38
```
</details>

---

