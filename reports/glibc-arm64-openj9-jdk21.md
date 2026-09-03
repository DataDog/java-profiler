---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-03 09:41:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 425 |
| Sample Rate | 7.08/sec |
| Health Score | 442% |
| Threads | 9 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 12 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (7 unique values: 24-32 cores)</summary>

```
1788442614 30
1788442619 28
1788442624 28
1788442629 28
1788442634 28
1788442639 28
1788442644 28
1788442649 25
1788442654 25
1788442659 25
1788442664 25
1788442669 25
1788442674 25
1788442679 24
1788442684 24
1788442689 24
1788442694 24
1788442699 24
1788442704 24
1788442709 24
```
</details>

---

