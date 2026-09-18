---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 07:50:58 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 762 |
| Sample Rate | 12.70/sec |
| Health Score | 794% |
| Threads | 11 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (3 unique values: 43-55 cores)</summary>

```
1789731847 43
1789731852 43
1789731857 43
1789731862 43
1789731867 43
1789731872 43
1789731877 43
1789731882 43
1789731887 43
1789731892 43
1789731898 43
1789731903 43
1789731908 43
1789731913 43
1789731918 43
1789731923 45
1789731928 45
1789731933 45
1789731938 45
1789731943 55
```
</details>

---

