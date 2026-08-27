---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-27 09:40:16 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 10 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 13 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1787837768 44
1787837773 44
1787837778 44
1787837783 44
1787837788 44
1787837793 44
1787837798 44
1787837803 44
1787837808 44
1787837813 44
1787837818 44
1787837823 44
1787837828 44
1787837833 44
1787837838 44
1787837843 44
1787837848 44
1787837853 44
1787837858 44
1787837863 44
```
</details>

---

