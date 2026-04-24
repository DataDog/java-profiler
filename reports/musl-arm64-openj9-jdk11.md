---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-24 11:36:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 250 |
| Sample Rate | 4.17/sec |
| Health Score | 261% |
| Threads | 10 |
| Allocations | 95 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 12 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777044699 64
1777044704 64
1777044709 64
1777044714 64
1777044719 64
1777044724 64
1777044729 64
1777044734 64
1777044739 64
1777044744 64
1777044749 64
1777044754 64
1777044759 64
1777044764 64
1777044769 64
1777044774 64
1777044779 64
1777044784 64
1777044789 64
1777044794 64
```
</details>

---

