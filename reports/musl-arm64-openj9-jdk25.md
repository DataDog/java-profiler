---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 10:30:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 161 |
| Sample Rate | 2.68/sec |
| Health Score | 168% |
| Threads | 13 |
| Allocations | 117 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1789655050 48
1789655055 48
1789655060 48
1789655065 47
1789655070 47
1789655075 47
1789655080 47
1789655085 47
1789655090 47
1789655095 47
1789655101 47
1789655106 47
1789655111 47
1789655116 47
1789655121 47
1789655126 48
1789655131 48
1789655136 48
1789655141 48
1789655146 48
```
</details>

---

