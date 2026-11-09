---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-09 17:14:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 9 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (3 unique values: 67-70 cores)</summary>

```
1794262156 69
1794262161 69
1794262166 69
1794262171 67
1794262176 67
1794262181 67
1794262186 67
1794262191 70
1794262196 70
1794262201 70
1794262206 70
1794262211 70
1794262216 70
1794262221 70
1794262226 70
1794262231 70
1794262236 70
1794262241 70
1794262246 70
1794262251 70
```
</details>

---

