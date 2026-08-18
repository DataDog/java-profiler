---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-18 05:26:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 11 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 11 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (4 unique values: 41-48 cores)</summary>

```
1787044732 48
1787044737 48
1787044742 48
1787044747 48
1787044752 48
1787044757 48
1787044762 48
1787044767 48
1787044772 48
1787044777 48
1787044782 48
1787044787 48
1787044792 48
1787044797 48
1787044802 47
1787044807 47
1787044812 47
1787044817 47
1787044822 47
1787044827 47
```
</details>

---

